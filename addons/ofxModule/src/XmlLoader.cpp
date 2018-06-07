/*
*  XMLLoader.cpp
*  example_server_sharedcanvas
*
*  Created by Brian Eschrich on 28.07.15
*  Copyright 2015 reddo UG. All rights reserved.
*
*/

#include "XmlLoader.h"

namespace ofxModule {

	XmlLoader::XmlLoader(ModuleRunner* moduleRunner_) {
		moduleRunner = moduleRunner_;
	}

	int XmlLoader::xmlHasModule(string modulname) {
		int ret = 0;
		if (XML.load("settings.xml")) {
			ofLogNotice("xmlloader", "settings.xml loaded!");
		}
		else {
			ofLogError("xmlloader", "settings.xml not found or error reading!");
		}
		auto xml_module = XML.find("//modules/module");
		for (auto & m : xml_module) {
			if (m.getAttribute("type").getValue() == modulname
				)
			{
				++ret;
			}
		}
		return ret;
	}

	/**
	* adds module to app
	*/
	void XmlLoader::addModule(ModuleRunnable* module) {
		moduleRunner->addModule(module);
		addToInputs(module);
	}


	void XmlLoader::addModule(ModuleDrawable* mdrawable) {
		moduleRunner->addModule(mdrawable);
		addToInputs(mdrawable);
	}

	bool XmlLoader::addToInputs(ModuleRunnable *module) {
		idMap.insert(pair<string, ModuleRunnable*>(module->getModuleName(), module));
		if (XML.load("settings.xml")) {
		}
		else {
			ofLogError("xmlloader", "settings.xml not found or error reading!");
		}
		auto xml_module = XML.find("//modules/module");
		for (auto & m : xml_module) {
			if (m.getAttribute("id").getValue() == module->getModuleName()
				|| (m.getAttribute("id").getValue() == ""
					&& m.getAttribute("type").getValue() == module->getModuleClass())
				)
			{
				createInputList(module);
				//return true;
			}
		}

		ofLogNotice("xmlloader", "Module: " + module->getModuleName() + " added");
		return true;
	}


	/**
	* registers events between classes
	*/
	void XmlLoader::createModuleConnections() {
		if (!inputs.empty()) {
			for (auto iter : inputs)
			{
				for (int i = 0; i<iter.second.size(); ++i) {
					if (idMap.find(iter.second[i]) != idMap.end()) {
						iter.first->registerModuleEvent(idMap[iter.second[i]]);
						ofLogNotice("XmlLoader::createModuleConnections", iter.first->getModuleName() + " <- " + iter.second[i]);
					}
					else {
						ofLogNotice("XmlLoader::createModuleConnections", iter.first->getModuleName() + " : no connection found for -> " + iter.second[i]);
					}
				}

			}
			for (auto iter : inputs)
			{
				iter.first->onAllModulesLoaded();
			}
		}

	}


	void XmlLoader::addInput(ModuleRunnable* module, string input)
	{
		vector<string> s;
		s.push_back(input);
		addInput(module, s);
	}
	void XmlLoader::addInput(ModuleRunnable* module, vector<string> inputs_)
	{
		inputs.insert(pair<ModuleRunnable*, vector<string> >(module, inputs_));
	}

	void XmlLoader::createInputList(ModuleRunnable* module) {
		cout << module->getModuleName() << endl;
		auto xml_module = XML.find("//modules/module");
		vector<string> s;
		for (auto& m : xml_module)
		{
			if (m.getAttribute("type").getValue() == module->getModuleName())
			{
				auto inputs = m.getChildren("input");
				int nSize = m.find("input").size();
				if (nSize>0)
				{
					for (const auto& input : inputs)
					{
						s.push_back(input.getAttribute("id").getValue());
					}
				}
			}
		}
		if (s.size() > 0) {
			addInput(module, s);
		}
		else {
			cout << "no con for " << module->getModuleName() << endl;
		}
	}

	/**
	* returns attribute value if existing
	*/
	string XmlLoader::getAttribute(string module, string attribute, int indexModule) {
		if (XML.load("settings.xml")) {
		}
		else {
			ofLogError("xmlloader", "settings.xml not found or error reading!");
		}
		int count = 0;

		auto xml_module = XML.find("//modules/module");
		for (auto & m : xml_module) {
			if (m.getAttribute("type").getValue() == module && count == indexModule)
			{
				string ret = m.getAttribute(attribute).getValue();
				return ret;
			}
			else if (m.getAttribute("type").getValue() == module && count < indexModule) {
				count++;
			}
		}
		return "attribute " + attribute + " not found";
	}

}
