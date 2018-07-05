import shiva

current_system_type = shiva.system_type.pre_update


def update():
    print("hello from python pre system")


def on_construct():
    print("hello from python pre system on_construct")


def on_destruct():
    print("hello from python pre system on_destruct")
