import { SHIPPING_COST, COUPON_DISCOUNT_RATE, COUPON_CODE } from "./constants";

export function calculateCartSummary(cartItems, coupon) {
	const subtotal = cartItems.reduce(
		(sum, item) => sum + item.price * item.quantity,
		0
	);

	const totalItems = cartItems.reduce((sum, item) => sum + item.quantity, 0);

	const discount = coupon === COUPON_CODE ? subtotal * COUPON_DISCOUNT_RATE : 0;

	const shipping = SHIPPING_COST;

	const total = subtotal - discount + shipping;

	return { subtotal, discount, shipping, total, totalItems };
}

export { SHIPPING_COST };