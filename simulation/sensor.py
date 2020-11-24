import argparse
import requests
import random
import time


def main():
    parser = argparse.ArgumentParser(description="Simulate a sensor.")
    parser.add_argument("--name", required=True)
    parser.add_argument("--id", type=int, required=True)
    parser.add_argument("--url", required=True)
    parser.add_argument("--min-value", type=int, required=True)
    parser.add_argument("--max-value", type=int, required=True)
    args = parser.parse_args()

    while True:
        value = random.randrange(args.min_value, args.max_value)
        r = requests.post(f"{args.url}/sensor/{args.id}/{value}", data=args.name)
        r.raise_for_status()
        time.sleep(5)


if __name__ == "__main__":
    main()