import { Component, css } from "dreamland/core";
import { argbFromHex, DynamicScheme, Hct, Icon, SchemeStyles, ToggleButton, Button, Variant, Card } from "m3-dreamland";
import playArrow from "@ktibow/iconset-material-symbols/play-arrow";
import pause from "@ktibow/iconset-material-symbols/pause";
import folderOpen from "@ktibow/iconset-material-symbols/folder-open-outline";

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

	use(this.playing).listen(x=>{
		(self as any).Module._set_enable_render_(x);
	});

	return (
		<div id="app">
			<SchemeStyles scheme={scheme} motion="expressive">
				<div class="bottom">
					<ToggleButton variant="elevated" icon="full" size="m" value={use(this.playing)} title={use(this.playing).andThen("Pause", "Resume")}>
						<Icon icon={use(this.playing).andThen(pause, playArrow)} />
					</ToggleButton>
				</div>
				<div class="corner">
					<Card variant="elevated">
						<div class="m3dl-font-headline-medium"><b>William Daniel Torus</b></div>
						<div>
							Defeating William Daniel with an invisible torus. Hold up/down arrow to morph the torus into a cube, and press left arrow to toggle between noise and smooth rendering.
						</div>
					</Card>
				</div>
			</SchemeStyles>
		</div>
	)
}
App.style = css`
	:scope :global(.m3dl-scheme-styles) {
		font: var(--m3dl-font);
		font-family: var(--m3dl-font);
		height: 100%;
		position: relative;
	}

	.bottom {
		position: absolute;
		bottom: 1rem;
		width: 100%;
		display: flex;
		justify-content: center;
		gap: 1rem;
		margin-bottom: 1rem;
	}
	.bottom > :global(.m3dl-button) { pointer-events: auto }

	.corner {
		position: absolute;
		right: 1rem;
		bottom: 1rem;
		max-width: 35%;
	}
`;
document.querySelector("#app").replaceWith(<App />);
