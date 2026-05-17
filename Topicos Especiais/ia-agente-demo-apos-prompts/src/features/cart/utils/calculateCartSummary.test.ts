import { describe, it, expect } from "vitest";
import { calculateCartSummary } from "./calculateCartSummary";
import { CartItem } from "../types";

describe("calculateCartSummary", () => {
	it("calculates total without coupon", () => {
		const cartItems: CartItem[] = [
			{ id: 1, name: "Teclado", price: 200, quantity: 1 },
		];
		const result = calculateCartSummary(cartItems, "");

		expect(result.subtotal).toBe(200);
		expect(result.discount).toBe(0);
		expect(result.shipping).toBe(40);
		expect(result.total).toBe(240);
	});

	it("applies 10% discount with URI10 coupon", () => {
		const cartItems: CartItem[] = [
			{ id: 1, name: "Teclado", price: 200, quantity: 1 },
		];
		const result = calculateCartSummary(cartItems, "URI10");

		expect(result.subtotal).toBe(200);
		expect(result.discount).toBe(20);
		expect(result.shipping).toBe(40);
		expect(result.total).toBe(220);
	});

	it("applies discount only on subtotal, not on shipping", () => {
		const cartItems: CartItem[] = [
			{ id: 1, name: "Teclado", price: 100, quantity: 1 },
		];
		const result = calculateCartSummary(cartItems, "URI10");

		const expectedTotal = 100 - 10 + 40;
		expect(result.total).toBe(expectedTotal);
		expect(result.shipping).toBe(40);
	});

	it("multiplies price by quantity for each item", () => {
		const cartItems: CartItem[] = [
			{ id: 1, name: "Mouse", price: 100, quantity: 3 },
		];
		const result = calculateCartSummary(cartItems, "");

		expect(result.subtotal).toBe(300);
		expect(result.total).toBe(340);
	});

	it("calculates totalItems correctly", () => {
		const cartItems: CartItem[] = [
			{ id: 1, name: "Teclado", price: 200, quantity: 2 },
			{ id: 2, name: "Mouse", price: 100, quantity: 3 },
		];
		const result = calculateCartSummary(cartItems, "");

		expect(result.totalItems).toBe(5);
	});

	it("handles empty cart", () => {
		const cartItems: CartItem[] = [];
		const result = calculateCartSummary(cartItems, "URI10");

		expect(result.subtotal).toBe(0);
		expect(result.discount).toBe(0);
		expect(result.total).toBe(40);
		expect(result.totalItems).toBe(0);
	});
});