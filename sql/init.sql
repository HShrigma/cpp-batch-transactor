DROP TABLE IF EXISTS transactions;

CREATE TABLE transactions (
    id SERIAL PRIMARY KEY,
    user_id BIGINT NOT NULL,
    transaction_type TEXT NOT NULL CHECK (
        transaction_type IN ('credit', 'debit')
    ),
    amount REAL NOT NULL CHECK (
        amount > 0
    ),
    timestamp TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
);