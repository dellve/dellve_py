import os
import os.path
import pytest
import dellve

build_dir 	= "./build/dellve/test/python"
plugin_path = os.path.join(build_dir, "dellve_test_plugin.dellveplugin")

def test_plugin():
	plugin = dellve.Plugin(plugin_path)

	operation = plugin.get_operation("TestOperation")

	assert isinstance(operation, dellve.Operation)

def test_operation():
	plugin = dellve.Plugin(plugin_path)

	operation = plugin.get_operation("TestOperation")

	assert str(operation) == "<dellve.Operation TestOperation>"

def test_message_send_recv():
	plugin = dellve.Plugin(plugin_path)

	operation = plugin.get_operation("TestOperation")

	message = {'send': "Yo", 'recv': None}

	operation.set_recv_callback(lambda m: message.__setitem__('recv', m))

	operation.send(message['send'])

	assert message['send'] == message['recv']