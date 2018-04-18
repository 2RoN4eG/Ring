#ifndef CONTAINER_RING_H
#define CONTAINER_RING_H

template <typename TRingItemValue>
class Ring
{
    template <typename TItemValue>
    class Item
    {
        friend class Ring <TItemValue>;

        Item <TItemValue> * 	Next	= nullptr;
        Item <TItemValue> * 	Prev	= nullptr;

        TItemValue              Value;
    };

    unsigned int                _size	= 0;

    Item <TRingItemValue> *		_first 	= nullptr;

    Item <TRingItemValue> *		_last 	= nullptr;

    Item <TRingItemValue> *     _item   = nullptr;

public:
    Ring () = default;
    ~Ring ()
    {
    }

    int Insert (TRingItemValue & value)
    {
        // first -> ... -> last -> first

        if (_first == nullptr || _last == nullptr)
        {
            Item <TRingItemValue> * item = CreateItem (value);

            _first  = item;

            _last   = item;
        }
        else
        {
            Item <TRingItemValue> * item = CreateItem (value, _first, _last);

            _first->Prev = item;

            _last->Next = item;

            _last = item;
        }

        return ++_size;
    }

    int Size ()
    {
        return _size;
    }

    TRingItemValue & Next ()
    {
        if (_item == nullptr && _size != 0)
        {
            _item = _first;
        }

        Item <TRingItemValue> * item = _item;

        _item = _item->Next;

        return item->Value;
    }

    TRingItemValue & Prev ()
    {
        if (_item == nullptr && _size != 0)
        {
            _item = _first;
        }

        Item <TRingItemValue> * item = _item;

        _item = _item->Prev;

        return item->Value;
    }

    TRingItemValue & operator [] (const int index)
    {
        Item <TRingItemValue> * item = _first;

        if (index < 0)
        {
            int number = (-1 * index) % _size;

            while (number-- > 0)
            {
                item = item->Prev;
            }

            return item->Value;
        }
        else /// if (index >= 0)
        {
            int number = index % _size;

            while (number-- > 0)
            {
                item = item->Next;
            }
        }

        return item->Value;

        /// Функция может быть оптимизирована
        /// пример:
        /// {
        ///     return _vector [number % _size];
        /// }
        /// или
        /// {
        ///     number = number % _size;
        ///
        ///     Item <TRingItemValue> * item = _vector [number];
        ///
        ///     return item;
        /// }
    }

private:
    Item <TRingItemValue> * CreateItem (TRingItemValue & value)
    {
        Item <TRingItemValue> * item = new Item <TRingItemValue> ();

        item->Value = value;

        item->Next 	= item;
        item->Prev 	= item;

        return item;
    }

    Item <TRingItemValue> * CreateItem (TRingItemValue & value, Item <TRingItemValue> * next, Item <TRingItemValue> * prev)
    {
        Item <TRingItemValue> * item = new Item <TRingItemValue> ();

        item->Value		= value;

        item->Next 		= next;
        item->Prev      = prev;

        return item;
    }
};

#endif // CONTAINER_RING_H
