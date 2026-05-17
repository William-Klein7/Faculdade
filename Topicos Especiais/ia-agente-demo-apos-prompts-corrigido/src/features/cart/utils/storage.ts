import { STORAGE_KEY } from "./constants";
import { CartItem } from "../types";

interface StorageData {
	cartItems: CartItem[];
	coupon: string;
}

export function loadFromStorage(): StorageData {
	try {
		const stored = localStorage.getItem(STORAGE_KEY);
		if (stored) {
			const data = JSON.parse(stored);
			return {
				cartItems: data.cartItems || [],
				coupon: data.coupon || "",
			};
		}
	} catch (e) {
		console.warn("Erro ao carregar dados do localStorage:", e);
	}
	return { cartItems: [], coupon: "" };
}

export function saveToStorage(cartItems: CartItem[], coupon: string): void {
	try {
		localStorage.setItem(STORAGE_KEY, JSON.stringify({ cartItems, coupon }));
	} catch (e) {
		console.warn("Erro ao salvar dados no localStorage:", e);
	}
}