#pragma once
class AWidget;
class WidgetStorage final
{
public:
	WidgetStorage();
	~WidgetStorage();
	
	void Add(AWidget* widget);
	void Remove(AWidget* widget);
	AWidget* Get(const String& name);
	bool IsInStorage(AWidget* widget);
	bool IsInStorageByName(const String& name);
	void Clear();
	const List<AWidget*>& GetAll() const;
	
private:
	List<AWidget*> m_WidgetList;
	HashTable<String, AWidget*> m_WidgetTable;
};
