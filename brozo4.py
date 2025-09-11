from tkinter import *
from tkinter import ttk

root = Tk()
root.title("BS COMPUTER SCIENCE")
root.geometry("500x150")

label = ttk.Label(root, text = "BS5AA", font = ("Arial", 10, "bold"),
wraplength = 150)

label.pack()

btn = Button(root, text = "Male")
bt1 = Button(root, text = "Female")

btn.pack()
bt1.pack()
root.mainloop()