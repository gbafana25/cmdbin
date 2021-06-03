# cmdbin

Command line paste bin service (termbin clone).  Still work in progress.

## Usage
- To create a paste: `cat [filename] | nc [hostname] 5678`
	- shortened link is returned
- To request a paste: `curl [hostname]:5678/f/[shortened_url] > [file]`

## Storing pastes
	Pastes are stored in plain text in the `pastes/` folder, with the file name corresponding to its shortened link.  Shortened links are generated randomly and are stored in the file `test.db`.

## TODO
- When pastes are requested in a browser, garbage characters are printed after text (fix)
