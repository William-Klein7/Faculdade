export function CouponInput({ coupon, onCouponChange }) {
	return (
		<div style={{ marginTop: 24 }}>
			<input
				placeholder="Cupom"
				value={coupon}
				onChange={(event) => onCouponChange(event.target.value)}
			/>
		</div>
	);
}