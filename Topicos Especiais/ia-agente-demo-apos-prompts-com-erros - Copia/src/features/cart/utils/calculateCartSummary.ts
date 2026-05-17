import { CartItem, CartSummary } from "../types";
import { SHIPPING_COST, COUPON_DISCOUNT_RATE, COUPON_CODE, FREE_SHIPPING_COUPON_CODE } from "./constants";

export function calculateCartSummary(cartItems: CartItem[], coupon: string): CartSummary {
	const subtotal = cartItems.reduce(
		(sum, item) => sum + item.price * item.quantity,
		0
	);

	const totalItems = cartItems.reduce((sum, item) => sum + item.quantity, 0);

	let discount = 0;
	let shipping = SHIPPING_COST;

	if (coupon === COUPON_CODE) {
		discount = subtotal * COUPON_DISCOUNT_RATE;
	} else if (coupon === FREE_SHIPPING_COUPON_CODE) {
		shipping = 0;
	}

	const total = Math.max(0, subtotal - discount + shipping);

	return { subtotal, discount, shipping, total, totalItems };
}

export { SHIPPING_COST };