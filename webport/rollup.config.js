import nodeResolve from "@rollup/plugin-node-resolve";
import terser from "@rollup/plugin-terser";
import typescript from "@rollup/plugin-typescript";
import { defineConfig } from "rollup";

export default defineConfig([
	{
		input: "src/index.tsx",
		output: [{ file: "dist/index.js", sourcemap: true }],
		plugins: [
			nodeResolve(),
			typescript({
				include: "src/**/*",
				filterRoot: process.cwd(),
				tsconfig: import.meta.dirname + "/tsconfig.json",
			}),
			/*
			terser({
				parse: {},
				compress: {
					passes: 5,
					unsafe: true,
					unsafe_Function: true,
					unsafe_arrows: true,
					unsafe_comps: true,
					unsafe_math: true,
					unsafe_methods: true,
					unsafe_proto: true,
					unsafe_regexp: true,
					unsafe_symbols: true,
					unsafe_undefined: true,
				},
				mangle: {
					keep_classnames: false,
					keep_fnames: false,
					properties: {
						regex: /^_.*//*,
					},
				},
				format: {
					wrap_func_args: false,
					comments: false
				},
				module: true,
				ie8: false,
				safari10: false,
				ecma: 2022,
			}),
			*/
		],
	},
]);
