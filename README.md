# concurrent-kv-store
A concurrent key-value store built from scratch in C++, implementing Write-Ahead Logging for crash recovery and readers-writer locks for concurrent access.

## Features
This project implements a concurrent key-value store with the following features:
1. PUT: Inserts a key-value pair into the store.
2. GET: Retrieves the value associated with a key.
3. DELETE: Deletes a key-value pair from the store.
4. Recovery: Restores the store to a consistent state after a crash.

## Architecture
The store is built around two core classes: StorageEngine and WAL. StorageEngine owns an in-memory unordered_map protected by a shared_mutex for concurrent access. WAL handles append-only logging to disk and replays the log on startup to restore state after a crash.

## Build & Run
```bash
git clone https://github.com/danysthename/concurrent-kv-store
cd concurrent-kv-store
mkdir build
cd build
cmake ..
make
./kv-store
```

## Tests
```bash
./correctness_test
./recovery_write
./recovery_read
./bench
```

To build with ThreadSanitizer:
```bash
cd build
make clean
make VERBOSE=1 CXXFLAGS="-fsanitize=thread"
```

## Benchmarks
    PUT: ~150k ops/sec
    GET: ~1.5M ops/sec
    Concurrent: ~250k ops/sec

## Desing Decisions
WAL is implemented before hash map so that:
    1.PUT is called
    2.WAL is written to disk
    3.Process crashes before hash map is updated
    4.On restart, RecoveryManager replays the WAL
    5.The PUT is reapplied which implies no data is lost.
If it was the other way round (hash map first):
    1.PUT is called
    2.hash map is updated
    3.Process crashes before WAL is written to disk
    4.On restart, RecoveryManager does not replay the WAL
    5.The PUT is not reapplied which implies data is lost.

shared_mutex is used because it allows:
    Multiple readers at a time
    Only one writer at a time



