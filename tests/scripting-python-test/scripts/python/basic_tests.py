import shiva


def test_create_entity():
    result = shiva.ett_registry.create()
    res = shiva.ett_registry.valid(result)
    assert res, "res should be true"
    return res


def test_destroy_entity():
    result = shiva.ett_registry.create()
    assert shiva.ett_registry.nb_entities() == 1, "should be 1"
    shiva.ett_registry.destroy(result)
    assert shiva.ett_registry.nb_entities() == 0, "should be 0"
    return True


def test_component():
    entity_id = shiva.ett_registry.create()
    component = shiva.ett_registry.add_layer_1_component(entity_id)
    same_component = shiva.ett_registry.get_layer_1_component(entity_id)
    assert shiva.ett_registry.layer_1_id() == 0, "should be 0"
    assert shiva.ett_registry.has_layer_1_component(entity_id), "should be true"
    shiva.ett_registry.remove_layer_1_component(entity_id)
    assert not shiva.ett_registry.has_layer_1_component(entity_id), "should be false"
    return True


def functor(entity_id):
    print(entity_id)
    shiva.ett_registry.destroy(entity_id)


def test_for_each():
    for i in range(1, 11):
        id = shiva.ett_registry.create()
        shiva.ett_registry.add_layer_1_component(id)
    assert shiva.ett_registry.nb_entities() == 10, "should be 10"
    shiva.ett_registry.for_each_entities_which_have_layer_1_component(functor)
    assert shiva.ett_registry.nb_entities() == 0, "should be 0"
    return True


def test_for_each_runtime():
    for i in range(1, 11):
        id = shiva.ett_registry.create()
        if i == 4:
            shiva.ett_registry.add_layer_3_component(id)
        else:
            shiva.ett_registry.add_layer_1_component(id)
            shiva.ett_registry.add_layer_2_component(id)
    table = [shiva.ett_registry.layer_1_id(), shiva.ett_registry.layer_2_id()]
    print("nb entities {}", shiva.ett_registry.nb_entities())
    assert shiva.ett_registry.nb_entities() == 10, "should be 10"
    shiva.ett_registry.for_each_runtime(table, functor)
    assert shiva.ett_registry.nb_entities() == 1, "should be 1"
    return True
