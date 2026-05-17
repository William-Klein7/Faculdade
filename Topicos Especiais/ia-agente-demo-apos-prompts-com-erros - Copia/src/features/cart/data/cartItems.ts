import { CartItem } from "../types";

export const availableProducts: Omit<CartItem, "quantity">[] = [
	{ id: 1, name: "Teclado", price: 200 },
	{ id: 2, name: "Mouse", price: 100 },
];