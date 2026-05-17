import { CartItem } from "./CartItem";

export function CartList({ cartItems, onUpdateQuantity, onRemove }) {
	if (cartItems.length === 0) {
		return <p>Carrinho vazio</p>;
	}

	return (
		<>
			{cartItems.map((item) => (
				<CartItem
					key={item.id}
					item={item}
					onUpdateQuantity={onUpdateQuantity}
					onRemove={onRemove}
				/>
			))}
		</>
	);
}