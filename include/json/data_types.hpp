#ifndef __JSON_DATA_TYPES_HPP__
#define __JSON_DATA_TYPES_HPP__

#include <vector>
#include <variant>
#include <string>
#include <map>

namespace json {
    using JsonTypes = std::variant<bool, double, std::string>;

    struct JsonNode: protected std::pair<JsonTypes*, std::vector<JsonNode>*> {
        JsonNode(JsonTypes* value, std::vector<JsonNode>* childs);
        JsonNode(const JsonTypes& value, const std::vector<JsonNode>& childs);
        JsonNode(JsonTypes&& value, std::vector<JsonNode>&& childs);
        JsonNode(const JsonNode& copy);
        JsonNode(JsonNode&& moved);

        virtual ~JsonNode();

        JsonNode& operator=(const JsonNode& copy);

        const JsonTypes& getValue() const;
        const std::vector<JsonNode>& getChilds() const;

        virtual bool isLeaf() const = 0;
        virtual bool isRoot() const = 0;

        virtual JsonNode& find(const JsonTypes& val) const = 0;
    };

    struct JsonRoot: public JsonNode {
        JsonRoot(std::vector<JsonNode>* childs);
        JsonRoot(const std::vector<JsonNode>& childs);
        JsonRoot(std::vector<JsonNode>&& childs);

        virtual bool isLeaf() const override;
        virtual bool isRoot() const override;

        virtual JsonNode& find(const JsonTypes& val) const override;
    };

    struct JsonLeaf: public JsonNode {
        JsonLeaf(JsonTypes* value);
        JsonLeaf(const JsonTypes& value);
        JsonLeaf(JsonTypes&& value);

        virtual bool isLeaf() const override;
        virtual bool isRoot() const override;

        virtual JsonNode& find(const JsonTypes& val) const override;
    };

    struct JsonIntermediateNode: public JsonNode {
        virtual bool isLeaf() const override;
        virtual bool isRoot() const override;

        virtual JsonNode& find(const JsonTypes& val) const override;
    };

    class Json {
    static std::vector<std::string>* _split(std::string str);

    protected:
        const JsonRoot* root;

    public:
        Json(const JsonRoot* root);
        Json(const Json& copy);
        Json(Json&& moved);

        virtual ~Json();

        /**
         *  Ищет узел по строке вида: <"node_string_value":'node_string_value':node_number_or_bool_value...> 
         */
        JsonNode& find(std::string key) const;
    };  
}

#endif