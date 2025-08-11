import { Component, css } from "dreamland/core";
import { argbFromHex, DynamicScheme, Hct, Icon, SchemeStyles, ToggleButton, Variant } from "m3-dreamland";
import playArrow from "@ktibow/iconset-material-symbols/play-arrow";
import pause from "@ktibow/iconset-material-symbols/pause";

let scheme = new DynamicScheme({
	sourceColorHct: Hct.fromInt(argbFromHex("CBA6F7")),
	contrastLevel: 0,
	specVersion: "2025",
	variant: Variant.TONAL_SPOT,
	isDark: true,
});

let canvasElement = document.querySelector("canvas.emscripten");
canvasElement.addEventListener("webglcontextlost", (e) => {
	alert('WebGL context lost. You will need to reload the page.');
	e.preventDefault();
}, false);

(self as any).Module = {
	print(...args: any[]) {
		console.log(...args);
	},
	canvas: canvasElement,
};

const App: Component<{}, { playing: boolean, }> = function() {
	this.playing = true;

	return (
		<div id="app">
			<SchemeStyles scheme={scheme} motion="expressive">
				<div class="bottom">
					<ToggleButton variant="elevated" icon="full" size="xl" value={use(this.playing)}>
						<Icon icon={use(this.playing).andThen(pause, playArrow)} />
					</ToggleButton>
				</div>
			</SchemeStyles>
		</div>
	)
}
App.style = css`
	:scope :global(.m3dl-scheme-styles) {
		font: var(--m3dl-font);
		height: 100%;
		display: flex;
		flex-direction: column-reverse;
	}

	.bottom {
		display: flex;
		justify-content: center;
		margin-bottom: 1rem;
	}
	.bottom > :global(.m3dl-button) { pointer-events: auto }
`;
document.querySelector("#app").replaceWith(<App />);
