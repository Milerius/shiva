import shiva

current_system_type = shiva.system_type.post_update


def update():
    print("hello from python post system")


def on_construct():
    print("hello from python post system on_construct")


def on_destruct():
    print("hello from python post system on_destruct")
