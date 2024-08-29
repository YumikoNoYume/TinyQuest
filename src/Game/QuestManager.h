#pragma once

#include <vector>
#include <algorithm>
#include "Utilities.h"
#include "TextManager.h"

class Quest {
public:
	virtual bool CheckStatus(const std::string& object_to_check) const = 0;
	virtual bool CheckStatus() const = 0;
	virtual void SetStatus(bool status_to_set, const std::string& object_to_set) = 0;
	virtual void SetStatus(std::size_t index_to_set) = 0;
};

class Quest1 : public Quest{
public:
	static Quest1& GetInst();
	bool CheckStatus(const std::string& object_to_check) const override;
	bool CheckStatus() const override;
	void SetStatus(bool status_to_set, const std::string& object_to_set) override;
	void SetStatus(std::size_t index_to_set) override;
private:
	Quest1() = default;
	std::vector<std::size_t> sequence;
	bool is_door_opened = false;
};

class Quest2 : public Quest {
public:
	static Quest2& GetInst();
	bool CheckStatus(const std::string& object_to_check) const override;
	bool CheckStatus() const override;
	void SetStatus(bool status_to_set, const std::string& object_to_set) override;
	void SetStatus(std::size_t index_to_set) override;
private:
	Quest2();
	std::unordered_map<std::string, bool> steps;
};

class Quest3 : public Quest {
public:
	static Quest3& GetInst();
	bool CheckStatus(const std::string& object_to_check) const override;
	bool CheckStatus() const override;
	void SetStatus(bool status_to_set, const std::string& object_to_set) override;
	void SetStatus(std::size_t index_to_set) override;
private:
	Quest3();
	std::unordered_map<std::string, bool> steps;
};

class Quest4 : public Quest {
public:
	static Quest4& GetInst();
	bool CheckStatus(const std::string& object_to_check) const override;
	bool CheckStatus() const override;
	void SetStatus(bool status_to_set, const std::string& object_to_set) override;
	void SetStatus(std::size_t index_to_set) override;
private:
	Quest4() = default;
	std::vector<std::size_t> sequence;
	bool is_door_opened = false;
};

Quest& GetQuest(std::size_t quest_to_get);