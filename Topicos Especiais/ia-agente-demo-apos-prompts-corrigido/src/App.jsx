import { useCart, CartList, CartSummary, availableProducts } from "./features/cart/index.ts";

function App() {
	const {
		cartItems,
		subtotal,
		discount,
		shipping,
		total,
		totalItems,
		applyCoupon,
		coupon,
		addToCart,
		removeFromCart,
		updateQuantity,
		clearCart,
	} = useCart();

	return (
		<main style={{ padding: 32, fontFamily: "Arial" }}>
			<h1>Produtos Disponíveis</h1>
			<div style={{ marginBottom: 24 }}>
				{availableProducts.map((product) => (
					<div key={product.id} style={{ marginBottom: 8 }}>
						<span>
							{product.name} - R$ {product.price.toFixed(2)}
						</span>
						<button
							onClick={() => addToCart(product)}
							style={{ marginLeft: 8 }}
						>
							Adicionar
						</button>
					</div>
				))}
			</div>

			<h1>Carrinho</h1>
			<CartList
				cartItems={cartItems}
				onUpdateQuantity={updateQuantity}
				onRemove={removeFromCart}
			/>

			<CartSummary
				subtotal={subtotal}
				discount={discount}
				shipping={shipping}
				total={total}
				totalItems={totalItems}
				coupon={coupon}
				onApplyCoupon={applyCoupon}
				onClearCart={clearCart}
			/>
		</main>
	);
}

export default App;