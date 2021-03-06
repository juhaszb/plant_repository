import argparse
import bottle
import requests


@bottle.post("/send/<action:int>/")
def send(action):
    if action == 1:
        print("Action request received: increase")
    elif action == -1:
        print("Action request received: decrease")
    else:
        bottle.abort(400)


def main():
    parser = argparse.ArgumentParser(description="Simulate an actor.")
    parser.add_argument("--id", type=int, required=True)
    parser.add_argument("--host", required=True)
    parser.add_argument("--port", type=int, required=True)
    parser.add_argument("--server-url", required=True)
    parser.add_argument("--sensor-id", type=int, required=True)
    args = parser.parse_args()

    r = requests.put(
        f"{args.server_url}/register/{args.id}/{args.sensor_id}/", data=str(args.port)
    )
    print(r.text)

    bottle.run(host=args.host, port=args.port)


if __name__ == "__main__":
    main()
