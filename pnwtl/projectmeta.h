#ifndef projectmeta_h__included_49A5C619_DF7C_44c3_B139_7F26780C832E
#define projectmeta_h__included_49A5C619_DF7C_44c3_B139_7F26780C832E

namespace Projects
{

typedef struct tagProjectWriter* ProjectWriter;

class XmlNode;
class XmlAttribute;

typedef std::list<XmlNode*>			LIST_NODES;
typedef std::list<XmlAttribute*>	LIST_ATTRS;

typedef LIST_NODES::iterator		XN_IT;
typedef LIST_NODES::const_iterator	XN_CIT;

typedef LIST_ATTRS::const_iterator	XA_IT;

class XmlNode
{
	public:
		XmlNode(LPCTSTR qualifiedName);
		XmlNode(LPCTSTR lpszNamespace, LPCTSTR lpszName);
		XmlNode(const XmlNode& copy);
		~XmlNode();

		XmlNode& operator = (const XmlNode& copy);
		
		void Write(ProjectWriter writer);

		void AddAttributes(XMLAttributes& atts);
		void AddChild(XmlNode* pChild);

		XmlNode* GetParent();
		LIST_NODES& GetChildren();

		LPCTSTR GetText();
		void SetText(LPCTSTR text);

		bool Matches(LPCTSTR ns, LPCTSTR name);

	protected:
		void clear();

	protected:
		tstring		sNamespace;
		tstring		sName;
		tstring		sText;

		XmlNode*	pParent;
		
		LIST_NODES	children;
		LIST_ATTRS	attributes;
};

class XmlAttribute
{
	public:
		XmlAttribute(LPCTSTR lpszNamespace, LPCTSTR lpszName, LPCTSTR lpszValue);
		XmlAttribute(const XmlAttribute& copy);

		XmlAttribute& operator = (const XmlAttribute& copy);

		void Write(ProjectWriter writer);

	protected:
		tstring		sNamespace;
		tstring		sName;
		tstring		sValue;
};

class UserData
{
	public:
		~UserData();
		
		UserData& operator = (const UserData& copy);

		void Add(XmlNode* node);

		const LIST_NODES& GetNodes();

		const int GetCount();

		void Write(ProjectWriter writer);

		bool Lookup(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value, bool defval);
		int Lookup(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value, int defval);
		LPCTSTR Lookup(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value, LPCTSTR defval);

		void Set(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value, bool val);
		void Set(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value, int val);
		void Set(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value, LPCTSTR val);

		XmlNode* GetCategoryNode(LPCTSTR ns, LPCTSTR group, LPCTSTR category);
		XmlNode* GetGroupNode(LPCTSTR ns, LPCTSTR group);

		XN_CIT	begin();
		XN_CIT	end();

	protected:
		void clear();
		XmlNode* locate(const LIST_NODES& nodes, LPCTSTR ns, LPCTSTR node);
		XmlNode* lookUp(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value);
		XmlNode* lookUpOrCreate(LPCTSTR ns, LPCTSTR group, LPCTSTR category, LPCTSTR value);

	protected:
		LIST_NODES nodes;
		//LIST_ATTRS attrs;
};

}

#endif //#ifndef projectmeta_h__included_49A5C619_DF7C_44c3_B139_7F26780C832E