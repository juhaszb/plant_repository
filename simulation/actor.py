import argparse
import bottle
import requests


@bottle.post("/send")
def send():
    print("Action request received")


def main():
    parser = argparse.ArgumentParser(description="Simulate a sensor.")
    parser.add_argument("--id", type=int, required=True)
    parser.add_argument("--host", required=True)
    parser.add_argument("--port", type=int, required=True)
    parser.add_argument("--server-url", required=True)
    parser.add_argument("--sensor-id", type=int, required=True)
    args = parser.parse_args()

    requests.post(
        f"{args.server_url}/register/{args.id}/{args.sensor_id}", data=str(args.port)
    )

    bottle.run(host=args.host, port=args.port)


if __name__ == "__main__":
    main()