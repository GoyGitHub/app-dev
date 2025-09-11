from tkinter import *
from tkinter import ttk

root = Tk()
root.title("BS COMPUTER SCIENCE")
root.geometry("500x150")

label = ttk.Label(root, text = "MAIN MENU", font = ("Cooper Black", 10,),
wraplength = 150)

label.pack()

btn1 = Button(root, text = "TMS APPLICATION")
btn2 = Button(root, text = "HUMIDITY AND TEMPERATURE APPLICATION")
btn3 = Button(root, text = "LOCK / UNLOCK SYSTEM")
btn4 = Button(root, text = "ITEM DETECTOR SYSTEM")
btn5 = Button(root, text = "DISTANCE MEASURE SYSTEM")


btn1.pack()
btn2.pack()
btn3.pack()
btn4.pack()
btn5.pack()
root.mainloop()