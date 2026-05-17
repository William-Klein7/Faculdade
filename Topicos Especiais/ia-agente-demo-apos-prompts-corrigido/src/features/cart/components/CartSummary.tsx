import { formatCurrency } from "../utils";
import { CouponInput } from "./CouponInput";

interface CartSummaryProps {
	subtotal: number;
	discount: number;
	shipping: number;
	total: number;
	totalItems: number;
	coupon: string;
	onApplyCoupon: (code: string) => void;
	onClearCart: () => void;
}

export function CartSummary({ subtotal, discount, shipping, total, coupon, onApplyCoupon, onClearCart, totalItems }: CartSummaryProps) {
	return (
		<div>
			<CouponInput coupon={coupon} onCouponChange={onApplyCoupon} />

			<p>Subtotal: {formatCurrency(subtotal)}</p>
			<p>Frete: {formatCurrency(shipping)}</p>
			<p>Desconto: {formatCurrency(discount)}</p>
			<h2>Total: {formatCurrency(total)}</h2>
			<p>Itens: {totalItems}</p>

			{totalItems > 0 && (
				<button onClick={onClearCart} style={{ marginTop: 16 }}>
					Limpar Carrinho
				</button>
			)}
		</div>
	);
}