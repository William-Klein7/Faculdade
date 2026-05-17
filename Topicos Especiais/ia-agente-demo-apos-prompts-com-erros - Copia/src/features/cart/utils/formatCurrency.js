export function formatCurrency(value) {
	return `R$ ${value.toFixed(2).replace(".", ",")}`;
}