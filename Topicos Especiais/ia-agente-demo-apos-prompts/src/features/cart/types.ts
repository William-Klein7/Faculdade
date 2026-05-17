export interface CartItem {
	id: number;
	name: string;
	price: number;
	quantity: number;
}

export interface CartSummary {
	subtotal: number;
	discount: number;
	shipping: number;
	total: number;
	totalItems: number;
}

export type CouponCode = "URI10" | "";

export interface CartStorageData {
	cartItems: CartItem[];
	coupon: CouponCode;
}