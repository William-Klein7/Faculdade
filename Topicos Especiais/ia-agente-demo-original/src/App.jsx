import { useState } from "react";

const products = [
	{ id: 1, name: "Teclado", price: 200 },
	{ id: 2, name: "Mouse", price: 100 },
];

function App() {
	const [coupon, setCoupon] = useState("");

	const shipping = 40;
	const subtotal = products.reduce((sum, product) => sum + product.price, 0);

	const discount = coupon === "URI10" ? subtotal * 0.1 : 0;

	const total = subtotal - discount + shipping;

	return (
		<main style={{ padding: 32, fontFamily: "Arial" }}>
			<h1>Carrinho</h1>

			{products.map((product) => (
				<div key={product.id}>
					<p>
						{product.name} - R$ {product.price.toFixed(2)}
					</p>
				</div>
			))}

			<input
				placeholder="Cupom"
				value={coupon}
				onChange={(event) => setCoupon(event.target.value)}
			/>

			<p>Subtotal: R$ {subtotal.toFixed(2)}</p>
			<p>Frete: R$ {shipping.toFixed(2)}</p>
			<p>Desconto: R$ {discount.toFixed(2)}</p>
			<h2>Total: R$ {total.toFixed(2)}</h2>
		</main>
	);
}

export default App;
