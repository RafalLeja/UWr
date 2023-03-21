namespace Interfejs
{
    interface IListCollection<T>
    {
        void Remove(T value);
        void Show();
        bool IsEmpty();
    }
}