# sushi-go

[![Greenkeeper badge](https://badges.greenkeeper.io/noRubidium/sushi-go.svg)](https://greenkeeper.io/)
[![Build Status](https://travis-ci.org/noRubidium/sushi-go.svg?branch=master)](https://travis-ci.org/noRubidium/sushi-go)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/noRubidium/sushi-go.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/noRubidium/sushi-go/alerts/)
[![Language grade: JavaScript](https://img.shields.io/lgtm/grade/javascript/g/noRubidium/sushi-go.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/noRubidium/sushi-go/context:javascript)
## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```

After you see the webpack compilation succeed (the `npm run webpack` step), open up `build/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.

## Run Project with Server

To run with the webpack development server run `npm run server` and view in the browser at http://localhost:8000. Running in this environment provides hot reloading and support for routing; just edit and save the file and the browser will automatically refresh.

Note that any hot reload on a route will fall back to the root (`/`), so `ReasonReact.Router.dangerouslyGetInitialUrl` will likely be needed alongside the `ReasonReact.Router.watchUrl` logic to handle routing correctly on hot reload refreshes or simply opening the app at a URL that is not the root.

To use a port other than 8000 set the `PORT` environment variable (`PORT=8080 npm run server`).

## Build for Production

```sh
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version as well as copy `src/index.html` into `build/`. You can then deploy the contents of the `build` directory (`index.html` and `Index.js`).

If you make use of routing (via `ReasonReact.Router` or similar logic) ensure that server-side routing handles your routes or that 404's are directed back to `index.html` (which is how the dev server is set up).

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.

## Design

The first iteration of thr game is aiming at making a single laptop game with players sitting around the laptop, taking turns to look at the laptop screen and play their cards. We aim to add all the cards and card play in this iteration, some special cards needs further considerstions of the design.

Server will be added in the next iteration and game logic will be moved to the backend to ensure the security of the game. In this case, we will add more plays and variants as well.
