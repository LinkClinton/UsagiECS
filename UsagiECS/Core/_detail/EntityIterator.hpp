﻿#pragma once

#include <iterator>

#include "EntityView.hpp"
#include "EntityDatabaseAccessInternal.hpp"

namespace usagi
{
    /**
     * \brief
     *
     * Iterator invalidation:
     * -- When Entity Page is created or destroyed.
     *
     * \tparam Database
     * \tparam ComponentAccess
     */
    template <
        typename Database,
        typename ComponentAccess
    >
        class EntityIterator
        : protected EntityDatabaseAccessInternal<Database>
    {
    public:
        using DatabaseT = Database;
        using ComponentAccessT = ComponentAccess;
        using PageIteratorT = typename DatabaseT::EntityPageIteratorT;
        using EntityPageT = typename DatabaseT::EntityPageT;
        using EntityIndexT = typename EntityPageT::EntityIndexT;

        // Standard Iterator Traits

        // todo: fix: in fact, this iterator returns a proxy object when dereferenced. since the proxy object is actually not a reference, this iterator does not satisfy any iterator category requirement.
        // boost::single_pass_traversal_tag
        using iterator_category = std::forward_iterator_tag;
        using value_type = EntityView<DatabaseT, ComponentAccessT>;
        using difference_type = std::ptrdiff_t;
        using pointer = void;
        using reference = value_type;

    protected:
        PageIteratorT   mPageCursor;
        EntityIndexT    mIndexInPage = 0;

        auto currentView() const
        {
            assert(this->mDatabase);
            assert(mPageCursor != this->entity_page_end());
            assert(mIndexInPage < DatabaseT::ENTITY_PAGE_SIZE);

            return EntityView<DatabaseT, ComponentAccessT>(
                this->mDatabase, &mPageCursor.ref(), mIndexInPage
                );
        }

        void next_page()
        {
            ++mPageCursor;
            mIndexInPage = 0;
        }

    public:
        EntityIterator() = default;

        explicit EntityIterator(DatabaseT* database)
            : EntityDatabaseAccessInternal<Database>(database)
        {
            mPageCursor = this->entity_page_begin();
        }

        EntityIterator(
            DatabaseT* database,
            PageIteratorT page_cursor,
            const EntityIndexT index_in_page)
            : EntityDatabaseAccessInternal<Database>(database)
            , mPageCursor(std::move(page_cursor))
            , mIndexInPage(index_in_page)
        {
        }

        EntityIterator& operator++()
        {
            assert(mPageCursor != this->entity_page_end());

            ++mIndexInPage;
            if (mIndexInPage == DatabaseT::ENTITY_PAGE_SIZE)
            {
                next_page();
            }
            return *this;
        }

        EntityIterator operator++(int)
        {
            EntityIterator ret = *this;
            ++(*this);
            return ret;
        }

        reference operator*() const
        {
            return currentView();
        }

        // Equality Comparators

        friend bool operator==(
            const EntityIterator& lhs, const EntityIterator& rhs)
        {
            assert(lhs.mDatabase == rhs.mDatabase);

            return lhs.mPageCursor == rhs.mPageCursor
                && lhs.mIndexInPage == rhs.mIndexInPage;
        }

        friend bool operator!=(
            const EntityIterator& lhs, const EntityIterator& rhs)
        {
            return !(lhs == rhs);
        }
    };
}
