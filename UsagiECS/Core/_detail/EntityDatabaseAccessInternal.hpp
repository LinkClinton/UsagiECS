﻿#pragma once

namespace usagi
{
    template <typename Database>
    class EntityDatabaseAccessInternal
    {
    public:
        using DatabaseT = Database;

    protected:
        DatabaseT* mDatabase = nullptr;

        EntityDatabaseAccessInternal() = default;

        explicit EntityDatabaseAccessInternal(Database* database)
            : mDatabase(database)
        {
        }

        auto entity_page_begin() const
        {
            return entity_page_at_index(mDatabase->mFirstEntityPageIndex);
        }

        auto entity_page_end() const
        {
            return entity_page_at_index(DatabaseT::EntityPageT::INVALID_PAGE);
        }

        auto entity_page_at_index(const std::size_t index) const
        {
            return EntityPageIterator<DatabaseT>(
                mDatabase, index
                );
        }
    };
}
