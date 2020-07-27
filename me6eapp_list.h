/******************************************************************************/
/* ファイル名 : me6eapp_list.h                                                */
/* 機能概要   : 汎用リストクラス(双方向循環リスト)                            */
/* 修正履歴   : 2013.01.08 Y.Shibata 新規作成                                 */
/*            : 2016.04.15 H.Koganemaru 名称変更に伴う修正                    */
/*                                                                            */
/* ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU LIMITED 2013-2016                */
/******************************************************************************/
#ifndef ___ME6EAPP_LIST_H__
#define ___ME6EAPP_LIST_H__

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
//! 双方向循環リスト構造体
///////////////////////////////////////////////////////////////////////////////
struct me6e_list
{
    void*              data;  ///< データ
    struct me6e_list* prev;  ///< 前データへのポインタ
    struct me6e_list* next;  ///< 次データへのポインタ
};
typedef struct me6e_list me6e_list;

///////////////////////////////////////////////////////////////////////////////
//! 全要素巡回用のforeachマクロ
///////////////////////////////////////////////////////////////////////////////
#define me6e_list_for_each(__iterator, __list)	\
    for (__iterator = (__list)->next;           \
         __iterator != __list;                  \
         __iterator = __iterator->next)

///////////////////////////////////////////////////////////////////////////////
//! @brief リスト初期化関数
//!
//! リストを初期化する。
//!
//! @param [in] list 初期化するリスト
//!
//! @return なし
///////////////////////////////////////////////////////////////////////////////
static inline void me6e_list_init(struct me6e_list* list)
{
    list->data = NULL;
    list->next = list;
    list->prev = list;

    return;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief データ設定関数
//!
//! 引数で指定されたデータをリスト要素のデータとして設定する。
//!
//! @param [in] list データ設定先のリスト要素
//! @param [in] data 設定するデータ
//!
//! @return なし
///////////////////////////////////////////////////////////////////////////////
static inline void me6e_list_add_data(struct me6e_list* list, void* data)
{
    list->data = data;

    return;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief データ取得関数(先頭)
//!
//! リストの先頭のデータを取得する。
//!
//! @param [in] list  データ取得対象のリスト
//!
//! @return   リスト先頭のデータ
///////////////////////////////////////////////////////////////////////////////
static inline void* me6e_list_first_data(struct me6e_list* list)
{
    return list->next->data;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief 要素取得関数(末尾)
//!
//! リストの末尾のデータを取得する。
//!
//! @param [in] list  データ取得対象のリスト
//!
//! @return   リスト末尾のデータ
///////////////////////////////////////////////////////////////////////////////
static inline void* me6e_list_last_data(struct me6e_list* list)
{
    return list->prev->data;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief 空リストチェック関数
//!
//! リストが空かどうかをチェックする
//!
//! @param [in] list チェックするリスト
//!
//! @retval  true   リストが空。
//! @retval  false  リストが空ではない。
///////////////////////////////////////////////////////////////////////////////
static inline int me6e_list_empty(struct me6e_list* list)
{
    return list == list->next;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief 要素追加関数
//!
//! 引数で指定された要素をリストへ追加する
//!
//! @param [in] node 追加する要素
//! @param [in] prev 追加先のリストの前要素
//! @param [in] next 追加先のリストの次要素
//!
//! @return なし
///////////////////////////////////////////////////////////////////////////////
static inline void __me6e_list_add(
    struct me6e_list* node,
    struct me6e_list* prev,
    struct me6e_list* next
)
{
    next->prev = node;
    node->next = next;
    node->prev = prev;
    prev->next = node;

    return;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief 要素追加関数(先頭)
//!
//! 引数で指定された要素をリストの先頭へ追加する
//!
//! @param [in] list 追加先のリスト
//! @param [in] node 追加する要素
//!
//! @return なし
///////////////////////////////////////////////////////////////////////////////
static inline void me6e_list_add(struct me6e_list* list, struct me6e_list* node)
{
    __me6e_list_add(node, list, list->next);
    return;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief 要素追加関数(末尾)
//!
//! 引数で指定された要素をリストの末尾へ追加する
//!
//! @param [in] list 追加先のリスト
//! @param [in] node 追加する要素
//!
//! @return なし
///////////////////////////////////////////////////////////////////////////////
static inline void me6e_list_add_tail(struct me6e_list* list, struct me6e_list* node)
{
    __me6e_list_add(node, list->prev, list);
    return;
}

///////////////////////////////////////////////////////////////////////////////
//! @brief 要素削除関数
//!
//! 引数で指定された要素をリストから削除する
//!
//! @param [in] node 削除する要素
//!
//! @return なし
///////////////////////////////////////////////////////////////////////////////
static inline void me6e_list_del(struct me6e_list* node)
{
    struct me6e_list* next;
    struct me6e_list* prev;

    next       = node->next;
    prev       = node->prev;
    next->prev = prev;
    prev->next = next;

    return;
}

#endif // ___ME6EAPP_LIST_H__

