import shiva

current_system_type = shiva.system_type.logic_update


def update():
    print("hello from python logic system")


def on_construct():
    print("hello from python logic system on_construct")


def on_destruct():
    print("hello from python logic system on_destruct")
