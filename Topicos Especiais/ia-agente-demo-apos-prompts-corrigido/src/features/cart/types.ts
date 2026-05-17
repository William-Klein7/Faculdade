export interface CartItem {
	id: number;
	name: string;
	price: number;
	quantity: number;
	image?: string;
}

export interface CartSummary {
	subtotal: number;
	discount: number;
	shipping: number;
	total: number;
	totalItems: number;
}