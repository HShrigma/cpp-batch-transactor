# C++ Batch Transactor

A lightweight financial system that processes CSV transactions into a PostgreSQL database.

## Features
- 🚀 CSV to PostgreSQL pipeline
- ✅ Transaction validation
- ⏱️ Automatic timestamp handling
- 📊 Basic balance operations
- 🛢️ **Docker-first design** (no local PostgreSQL needed)
- 🔒 Configurable via `.env` (but ships with safe defaults)


## Quick Start

### Prerequisites
- Docker & Docker Compose
- C++20 compiler
- libpqxx (PostgreSQL C++ client)

### Running with Docker
1. #### Start the database
```bash
docker-compose up -d

# Set up environment (adjust values as needed)
cp .env.example .env
```
2. #### Build and run

**Option A:** Manual build
``` bash
mkdir -p build && cd build
cmake .. && make
./transactor
```

**Option B:** Use the Helper Script

```bash
chmod +x ./run_batch.sh  # Make executable
./run_batch.sh           # Builds and runs
```

## 🔧 Configuration

⚠️ This project does not set up an actual `.env` file  for the ease of use of the user.

The app uses sane defaults, but you can override them by creating a .env file:
```ini
DB_NAME=batch_db
DB_USER=batch_user
DB_PASSWORD=batch_pass
DB_HOST=localhost
DB_PORT=5432
```

## Project Structure

├── data/               # Sample CSV
├── src/
│   ├── io/             # CSV handling
│   └── transaction/    # Core logic
├── sql/                # Database schema
├── .env.example        # Config template
└── docker-compose.yaml # DB service

## Sample CSV Format

``` bash
user_id,type,amount,timestamp
1,credit,50.00,2023-01-01T00:00:00Z
2,debit,25.50,2023-01-01T00:01:00Z
```
## Development Notes

- Compile with CMake (C++20 required)
- `.CSV` files should be placed in data/
- Debug mode shows transaction details

## ⚠️ Safety Reminder

**This is a toy/educational project**

- 🔐 Default credentials are not secure for production.
- If you plan on using this for any purpose, make sure you configure:
    - an actual `.env` file.
    - the `docker-compose.yaml` to work with environment variables instead of literals.
## ⚖️ License
MIT License.