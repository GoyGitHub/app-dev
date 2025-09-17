import customtkinter as ctk
import sys
import os
import subprocess

# ======== OPEN TMS APP ========
def open_tms_app(menu_window):
    menu_window.withdraw()  # <-- Hide Main Menu instead of destroying it
    python_executable = sys.executable
    script_path = os.path.join(os.path.dirname(__file__), "tms_app.py")
    subprocess.Popen([python_executable, script_path])  # Launch tms_app.py

# ======== MAIN MENU WINDOW ========
def open_main_menu():
    menu_window = ctk.CTk()
    menu_window.title("Main Menu")
    menu_window.geometry("400x600")
    menu_window.configure(fg_color="#1a1a1a")

    cooper_black_font = ("Cooper Black", 24)
    button_font = ("Cooper Black", 14)

    ctk.CTkLabel(
        menu_window,
        text="MAIN MENU",
        font=cooper_black_font,
        text_color="white"
    ).pack(pady=30)

    # Buttons
    buttons = [
        ("TMS APPLICATION", lambda: open_tms_app(menu_window)),
        ("HUMIDITY & TEMPERATURE", None),
        ("LOCK / UNLOCK SYSTEM", None),
        ("ITEM DETECTOR SYSTEM", None),
        ("DISTANCE MEASURE SYSTEM", None)
    ]

    for text, command in buttons:
        btn = ctk.CTkButton(
            menu_window,
            text=text,
            font=button_font,
            width=260,
            height=55,
            corner_radius=18,
            fg_color="#00BFFF",
            hover_color="#009ACD",
            text_color="black",
            command=command
        )
        btn.pack(pady=12)

    menu_window.mainloop()

if __name__ == "__main__":
    open_main_menu()
