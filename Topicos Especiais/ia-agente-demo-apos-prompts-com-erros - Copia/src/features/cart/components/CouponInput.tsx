interface CouponInputProps {
	coupon: string;
	onCouponChange: (value: string) => void;
}

export function CouponInput({ coupon, onCouponChange }: CouponInputProps) {
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