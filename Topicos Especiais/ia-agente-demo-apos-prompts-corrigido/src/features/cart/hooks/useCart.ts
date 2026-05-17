import { useState, useMemo, useEffect } from "react";
import { calculateCartSummary, loadFromStorage, saveToStorage } from "../utils";
import { CartItem } from "../types";

interface Product {
	id: number;
	name: string;
	price: number;
	quantity?: number;
	image?: string;
}

export function useCart() {
	const [cartItems, setCartItems] = useState<CartItem[]>(() => loadFromStorage().cartItems);
	const [coupon, setCoupon] = useState<string>(() => loadFromStorage().coupon);

	useEffect(() => {
		saveToStorage(cartItems, coupon);
	}, [cartItems, coupon]);

	const addToCart = (product: Product) => {
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

	const { subtotal, discount, shipping, total, totalItems } = useMemo(
		() => calculateCartSummary(cartItems, coupon),
		[cartItems, coupon]
	);

	return {
		cartItems,
		subtotal,
		discount,
		shipping,
		total,
		totalItems,
		applyCoupon,
		coupon,
		addToCart,
		removeFromCart,
		updateQuantity,
		clearCart,
	};
}