#include <json/data_types.hpp>

#include <additionally/_string.hpp>
#include <json/parser.hpp>

#include <algorithm>
#include <stdexcept>

namespace json {
    JsonNode::JsonNode(JsonTypes* value, std::vector<JsonNode>* childs): std::pair<JsonTypes*, std::vector<JsonNode>*>(value, childs) {}

    JsonNode::JsonNode(const JsonTypes& value, const std::vector<JsonNode>& childs): std::pair<JsonTypes*, std::vector<JsonNode>*>(new JsonTypes(value), new std::vector<JsonNode>(childs)) {}

    JsonNode::JsonNode(JsonTypes&& value, std::vector<JsonNode>&& childs): std::pair<JsonTypes*, std::vector<JsonNode>*>(&value, &childs) {}

    JsonNode::JsonNode(const JsonNode& copy): std::pair<JsonTypes*, std::vector<JsonNode>*>(copy.first, copy.second) {}

    JsonNode::JsonNode(JsonNode&& moved): std::pair<JsonTypes*, std::vector<JsonNode>*>(std::move(moved.first), std::move(moved.second)) {}

    JsonNode::~JsonNode() {
        delete this->first;
        delete this->second;
    }

    JsonNode& JsonNode::operator=(const JsonNode& copy) {
        this->first = copy.first;
        this->second = copy.second;
    }

    const JsonTypes& JsonNode::getValue() const {
        return *this->first;
    }

    const std::vector<JsonNode>& JsonNode::getChilds() const {
        return *this->second;
    }


    // Если не будет работать, создать JsonEmptyNode.
    JsonRoot::JsonRoot(std::vector<JsonNode>* childs): JsonNode(nullptr, childs) {};

    JsonRoot::JsonRoot(const std::vector<JsonNode>& childs): JsonNode(nullptr, childs) {};

    JsonRoot::JsonRoot(std::vector<JsonNode>&& childs): JsonNode(std::move(nullptr), std::move(childs)) {};

    bool JsonRoot::isLeaf() const {
        return this->second->empty();
    }

    bool JsonRoot::isRoot() const {
        return true;
    }

    JsonNode& JsonRoot::find(const JsonTypes& val) const {
        std::vector<JsonNode>::iterator result = std::find_if(this->second->begin(), this->second->end(), [&val](const JsonNode& node){return node.getValue() == val;});

        if (result == this->second->end())
            throw std::runtime_error("[json::JsonRoot(extends JsonNode)::find]: У корня нет детей с таким значением.");

        return *result;
    }


    JsonLeaf::JsonLeaf(JsonTypes* value): JsonNode(value, nullptr) {};
    
    JsonLeaf::JsonLeaf(const JsonTypes& value): JsonNode(new JsonTypes(value), nullptr) {};

    JsonLeaf::JsonLeaf(JsonTypes&& value): JsonNode(&value, nullptr) {};

    bool JsonLeaf::isLeaf() const {
        return true;
    }

    bool JsonLeaf::isRoot() const {
        return false;
    }

    JsonNode& JsonLeaf::find(const JsonTypes& val) const {
        throw std::runtime_error("[json::JsonLeaf(extends JsonNode)::find]: У листьев нет детей!");
    }


    bool JsonIntermediateNode::isLeaf() const {
        return false;
    }

    bool JsonIntermediateNode::isRoot() const {
        return false;
    }

    JsonNode& JsonIntermediateNode::find(const JsonTypes& val) const {
        std::vector<JsonNode>::iterator result = std::find_if(this->second->begin(), this->second->end(), [&val](const JsonNode& node){return node.getValue() == val;});

        if (result == this->second->end())
            throw std::runtime_error("[json::JsonIntermediateNode(extends JsonNode)::find]: У промежуточного узла нет детей с таким значением.");

        return *result;
    }


    Json::Json(const JsonRoot* root): root(root) {}

    Json::Json(const Json& copy): root(new JsonRoot(copy.root->getChilds())) {}

    Json::Json(Json&& moved): root(moved.root) {}

    Json::~Json() {
        delete this->root;
    }


    JsonNode& Json::find(std::string key) const {
        additionally::Splitter* splitted = new additionally::Splitter(key.c_str(), ':');
        std::pair<const char*, const char*> raw_val;
        JsonNode& node = this->root->find(Parser::from_string_to_json_types(splitted->at(0).first, splitted->at(0).second));

        for (int k = 1; k < splitted->getLength(); k++) {
            raw_val = splitted->at(k);
            node = node.find(Parser::from_string_to_json_types(raw_val.first, raw_val.second));
        }

        return node;
    }
}