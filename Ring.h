#ifndef RING_H
#define RING_H

#include <iostream>

/// Контейнер с кольцевой организаией элементов
template <typename TRingElementItem>
class Ring
{
private:
    template <typename TElementItem>
    class Element
    {
        friend class Ring <TElementItem>;

        Element <TElementItem> *    Next            = nullptr;

        Element <TElementItem> *    Prev            = nullptr;

        TElementItem                Item;
    };

    unsigned int                    _size           = 0;

    Element <TRingElementItem> *    _first          = nullptr;

    Element <TRingElementItem> *    _last           = nullptr;

    Element <TRingElementItem> *    _element        = nullptr;

public:
    Ring () = default;
    ~Ring ()
    {
        while (_size-- > 0)
        {
            Element <TRingElementItem> * element = _first;

            _first = _first->Next;

            delete element;
        }
    }

    /// API - Кол-во элементов в кольце
    int Size ()
    {
        return _size;
    }

    /// API - Добавление нового элемента в кольцо (значение - item)
    int Insert (TRingElementItem & item)
    {
        // first -> ... -> last -> first

        Element <TRingElementItem> * element = nullptr;

        if (_first == nullptr)
        {
            element = CreateElement (item);

            _first  = element;
        }
        else
        {
            element = CreateElement (item, _first, _last);

            _first->Prev = element;

            _last->Next = element;
        }

        _last = element;

        return ++_size;
    }

    /// API - Удаление элемента из кольцо (если совпало значение - item)
    bool Remove (TRingElementItem & item)
    {
        return false;
    }

    /// API - Значение следующего элемента
    TRingElementItem & Next ()
    {
        if (_element == nullptr && _size != 0)
        {
            _element = _first;
        }

        Element <TRingElementItem> * element = _element;

        _element = _element->Next;

        return element->Item;
    }

    /// API - Значение предидущего элемента
    TRingElementItem & Prev ()
    {
        if (_element == nullptr && _size != 0)
        {
            _element = _first;
        }

        Element <TRingElementItem> * element = _element;

        _element = _element->Prev;

        return element->Item;
    }

    /// API - Получение элемента по индексу
    TRingElementItem & operator [] (const int index)
    {
        Element <TRingElementItem> * element = _first;

        if (index < 0)
        {
            int number = (-1 * index) % _size;

            while (number-- > 0)
            {
                element = element->Prev;
            }
        }
        else /// if (index >= 0)
        {
            int number = index % _size;

            while (number-- > 0)
            {
                element = element->Next;
            }
        }

        return element->Item;

        /// Функция может быть оптимизирована
        /// пример:
        /// {
        ///     return _vector [number % _size];
        /// }
        /// или
        /// {
        ///     number = number % _size;
        ///
        ///     Element <TRingElementitem> * Element = _vector [number];
        ///
        ///     return Element;
        /// }
    }

private:
    Element <TRingElementItem> * CreateElement (TRingElementItem & item)
    {
        Element <TRingElementItem> * element = new Element <TRingElementItem> ();

        element->Item   = item;

        element->Next   = element;
        element->Prev 	= element;

        return element;
    }

    Element <TRingElementItem> * CreateElement (TRingElementItem & item, Element <TRingElementItem> * next, Element <TRingElementItem> * prev)
    {
        Element <TRingElementItem> * element = new Element <TRingElementItem> ();

        element->Item   = item;

        element->Next   = next;
        element->Prev   = prev;

        return element;
    }
};

#endif // RING_H
