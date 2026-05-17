import { useState, useMemo, useEffect } from "react";
import { CartItem, CartSummary } from "../types";
import { calculateCartSummary, loadFromStorage, saveToStorage } from "../utils";

interface UseCartReturn {
	cartItems: CartItem[];
	subtotal: number;
	discount: number;
	shipping: number;
	total: number;
	totalItems: number;
	coupon: string;
	applyCoupon: (code: string) => void;
	addToCart: (product: Omit<CartItem, "quantity">) => void;
	removeFromCart: (productId: number) => void;
	updateQuantity: (productId: number, quantity: number) => void;
	clearCart: () => void;
}

export function useCart(): UseCartReturn {
	const [cartItems, setCartItems] = useState<CartItem[]>(() => loadFromStorage().cartItems);
	const [coupon, setCoupon] = useState<string>(() => loadFromStorage().coupon);

	useEffect(() => {
		saveToStorage(cartItems, coupon as "URI10" | "");
	}, [cartItems, coupon]);

	const addToCart = (product: Omit<CartItem, "quantity">) => {
		setCartItems((prev) => {
			const existing = prev.find((item) => item.id === product.id);
			if (existing) {
				return prev.map((item) =>
					item.id === product.id
						? { ...item, quantity: item.quantity + 1 }
						: item
				);
			}
			return [...prev, { ...product, quantity: 1 }];
		});
	};

	const removeFromCart = (productId: number) => {
		setCartItems((prev) => prev.filter((item) => item.id !== productId));
	};

	const updateQuantity = (productId: number, quantity: number) => {
		if (quantity <= 0) {
			removeFromCart(productId);
			return;
		}
		setCartItems((prev) =>
			prev.map((item) =>
				item.id === productId ? { ...item, quantity } : item
			)
		);
	};

	const clearCart = () => {
		setCartItems([]);
		setCoupon("");
	};

	const applyCoupon = (code: string) => {
		setCoupon(code);
	};

	const summary: CartSummary = useMemo(
		() => calculateCartSummary(cartItems, coupon),
		[cartItems, coupon]
	);

	return {
		cartItems,
		subtotal: summary.subtotal,
		discount: summary.discount,
		shipping: summary.shipping,
		total: summary.total,
		totalItems: summary.totalItems,
		applyCoupon,
		coupon,
		addToCart,
		removeFromCart,
		updateQuantity,
		clearCart,
	};
}