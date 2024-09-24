import argparse, json
import tkinter as tk
from src.app import App

def main(port):
    App.prepare_user_data()
    root = tk.Tk()
    app = App(root, port)
    root.protocol("WM_DELETE_WINDOW", app.on_close)
    root.mainloop()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--port', default=12345, type=int)
    
    args = parser.parse_args()
    main(args.port)
