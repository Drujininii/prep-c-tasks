template<class T>
class Tour_tree {
public:
    Tour_tree() {};

    Tour_tree(std::vector <T> &new_vector);

    ~Tour_tree() {};

private:
    std::vector <T> tree;
    int MIN_VALUE = -1;

    void tree_build(int left_idx, int last_lef_level_idx);

    void tree_sort(std::vector <T> &vector);

    T pop_max();

    int find_last_son(int first_idx);

    void branch_rebuild(int last_idx);
};


template<class T>
Tour_tree<T>::Tour_tree(std::vector <T> &vector) {
    int near_pow = 0;
    int size = vector.size();
    while (true) {
        if (size <= pow(2, near_pow))
            break;
        near_pow++;
    }
    int near_pow_value = (int) pow(2, near_pow);
    std::vector <T> elem(near_pow_value * 2 - 1);//размер испрввить
    tree = elem;
    int diff = near_pow_value - size;
    int offset = near_pow_value - 1;
    T min_value = vector[0];
    for (int i = 0; i < vector.size(); i++) {
        tree[offset + i] = vector[i];
        if (vector[i] < min_value)
            min_value = vector[i];
    }
    MIN_VALUE = min_value - 1;//небольшой костыль. если шаблон не числовой тип данных, то не работает.
    int tree_last_idx = tree.size() - 1;
    for (int i = 0; i < diff; i++)
        tree[tree_last_idx - i] = MIN_VALUE;
    tree_build(tree_last_idx / 2, tree_last_idx - 1);
    tree_sort(vector);
}


template<class T>
void Tour_tree<T>::tree_build(int idx, int last_idx) {
    if (idx == 0)
        return;
    int parent_idx = (idx - 1) / 2;
    if (tree[idx] > tree[idx + 1])
        tree[parent_idx] = tree[idx];
    else
        tree[parent_idx] = tree[idx + 1];
    if (idx == last_idx) {
        int next_level_parent = parent_idx / 2;
        last_idx = parent_idx - 1;
        tree_build(next_level_parent, last_idx);
        return;
    }
    tree_build(idx + 2, last_idx);
    return;
}


template<class T>
void Tour_tree<T>::tree_sort(std::vector <T> &vector) {
    int i = vector.size() - 1;
    T max_value;
    while (tree[0] != MIN_VALUE) {
        max_value = pop_max();
        vector[i] = max_value;
        i--;
    }
}

template<class T>
T Tour_tree<T>::pop_max() {
    T max_elem = tree[0];
    int idx = 0;
    int last_son_idx = find_last_son(idx);
    tree[last_son_idx] = MIN_VALUE;
    branch_rebuild(last_son_idx);
    return max_elem;
}


template<class T>
int Tour_tree<T>::find_last_son(int idx) {
    if ((idx + 1) * 2 > tree.size())
        return idx;
    int son_idx = (tree[idx * 2 + 1] == tree[idx]) ? (idx * 2 + 1) : (idx * 2 + 2);
    return find_last_son(son_idx);
}


template<class T>
void Tour_tree<T>::branch_rebuild(int idx) {
    if (idx == 0)
        return;
    if (idx % 2)
        idx++;
    if (tree[idx] > tree[idx - 1])
        tree[(idx - 1) / 2] = tree[idx];
    else
        tree[(idx - 1) / 2] = tree[idx - 1];
    branch_rebuild((idx - 1) / 2);
}
