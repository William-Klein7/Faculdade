const input = document.getElementById("pokemonInput");
const button = document.getElementById("searchBtn");
const pokemonNameDisplay = document.getElementById("pokemonName");
const pokemonImage = document.getElementById("pokemonImage");
const displayArea = document.getElementById("pokemonDisplay");
const errorMessage = document.getElementById("errorMessage");

button.addEventListener("click", () => {
	const query = input.value.trim().toLowerCase();

	if (query === "") {
		return;
	}

	errorMessage.textContent = "";

	fetch(`https://pokeapi.co/api/v2/pokemon/${query}`)
		.then((response) => {
			if (!response.ok) {
				throw new Error("Pokémon não encontrado! Verifique o nome ou ID.");
			}
			return response.json();
		})
		.then((data) => {
			const nomeCapitalizado =
				data.name.charAt(0).toUpperCase() + data.name.slice(1);

			pokemonNameDisplay.textContent = nomeCapitalizado;
			pokemonImage.src = data.sprites.front_default;

			displayArea.classList.remove("hidden");
		})
		.catch((error) => {
			displayArea.classList.add("hidden");
			errorMessage.textContent = error.message;
		});
});
