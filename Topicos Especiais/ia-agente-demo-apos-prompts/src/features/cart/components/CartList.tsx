import { CartItem as CartItemType } from "../types";
import { CartItem } from "./CartItem";

interface CartListProps {
	cartItems: CartItemType[];
	onUpdateQuantity: (productId: number, quantity: number) => void;
	onRemove: (productId: number) => void;
}

export function CartList({ cartItems, onUpdateQuantity, onRemove }: CartListProps) {
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