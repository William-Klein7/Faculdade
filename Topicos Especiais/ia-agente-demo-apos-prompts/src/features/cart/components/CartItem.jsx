import { formatCurrency } from "../utils";

export function CartItem({ item, onUpdateQuantity, onRemove }) {
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