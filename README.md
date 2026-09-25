# UCI GeoGuesser Backend

C++ API (Crow) and Postgres database for the UCI campus guessing game. Images are stored in Google Cloud Storage.

Frontend repo: [UCIGeoGuesser/frontend](https://github.com/UCIGeoGuesser/frontend)

## Setup

Install Docker, then add a `.env` file in `backend/`:

```bash
COMPOSE_FILE=../compose.yaml
BUCKET_NAME=your-bucket-name
```

Put the Google Cloud service account JSON at `backend/key-file.json` (this file is gitignored).

From `backend/`:

```bash
docker compose up --build
```

The API listens on port `18080`. Postgres listens on port `5432`.

See `backend/README.md` for run details, `backend/db/README.md` for the database, and `backend/api_documentation.md` for request and response schemas.

## Deploy

Pushes to `main` run `.github/workflows/deploy.yaml`, which SSHes to the Oracle Cloud VM and runs `scripts/deploy-backend.sh`.

The VM checkout at `ucigeoguesser` needs to track this repository:

```bash
git remote set-url origin https://github.com/UCIGeoGuesser/backend.git
```
