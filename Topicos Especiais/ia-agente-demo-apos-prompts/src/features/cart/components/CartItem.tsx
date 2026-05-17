import { CartItem as CartItemType } from "../types";
import { formatCurrency } from "../utils";

interface CartItemProps {
	item: CartItemType;
	onUpdateQuantity: (productId: number, quantity: number) => void;
	onRemove: (productId: number) => void;
}

export function CartItem({ item, onUpdateQuantity, onRemove }: CartItemProps) {
	return (
		<div style={{ marginBottom: 8 }}>
			<span>
				{item.name} - {formatCurrency(item.price)} x {item.quantity} = {formatCurrency(item.price * item.quantity)}
			</span>
			<button
				onClick={() => onUpdateQuantity(item.id, item.quantity - 1)}
				style={{ marginLeft: 8 }}
			>
				-
			</button>
			<span style={{ margin: "0 8px" }}>{item.quantity}</span>
			<button onClick={() => onUpdateQuantity(item.id, item.quantity + 1)}>
				+
			</button>
			<button
				onClick={() => onRemove(item.id)}
				style={{ marginLeft: 8, color: "red" }}
			>
				Remover
			</button>
		</div>
	);
}