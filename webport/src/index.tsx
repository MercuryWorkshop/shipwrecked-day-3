import { Component } from "dreamland/core";

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

const App: Component<{}> = function() {
	return (
		<div id="app">
		</div>
	)
}
document.querySelector("#app").replaceWith(<App />);
