<?php

use Drupal\Component\Utility\Html;
use Drupal\taxonomy\Entity\Term;
use Drupal\Core\Url;
use Drupal\Component\Serialization\Json;

use Drupal\Core\Template\Attribute;

use Drupal\drup\DrupViewsView;
use Drupal\drup\DrupViewsRows;
use Drupal\drup\DrupEntityField;
use Drupal\drup\DrupEntityImage;
use Drupal\drup\DrupCommon;
use Drupal\drup\DrupSite;

/**
 * Preprocess View
 *
 * @param $variables
 */
function drup_theme_preprocess_views_view(&$variables) {
    $drupViewsView = new DrupViewsView($variables);
    $variables = $drupViewsView->controller();
    
//    switch ($variables['view']->id()) {
//        case 'store_locators':
//            $variables['display_total_rows_count'] = \Drupal::translation()->formatPlural(
//                $variables['view']->total_rows,
//                '@count result founded.',
//                '@count results founded.'
//            );
//            if (empty($variables['view']->total_rows)) {
//                $variables['empty'] = t('No result match your search.');
//            }
//            break;
//    }
}

/**
 * Preprocess Rows
 *
 * @param $variables
 */
function drup_theme_preprocess_views_view_unformatted(&$variables) {
    $drupViewsRows = new DrupViewsRows($variables);
    $variables = $drupViewsRows->controller();
}

/**
 * Suggestions views
 */
function drup_theme_theme_suggestions_views_view_unformatted_alter(array &$suggestions, array &$variables) {
    switch ($variables['view']->id()) {
        case 'news':
            $variables['theme_hook'] = 'primary'; // hook_id
            $suggestions[] = 'views_view_unformatted__primary'; // template twig
            break;
    }
}


/**
 * Toutes les vues
 */
//function drup_theme_views_rows_controller($variables) {
//
//    return $variables;
//}

/**
 * Vue rows ""
 */
//function drup_theme_views_rows_controller__THEMEPARTIAL($variables) {
//
//    return $variables;
//}

/**
 * Vue ""
 */
//function drup_theme_views_rows_controller__VIEWID($variables) {
//
//    return $variables;
//}

/**
 * Vue + Display ""
 */
//function drup_theme_views_rows_controller__VIEWID__DISPLAYID($variables) {
//    $aliasManager = \Drupal::service('path.alias_manager');
//
//    $variables['block']['title']['value'] = t('Block title');
//    $variables['rows_attributes']->addClass('list--primary');
//
//    if (!empty($variables['view']->result)) {
//        foreach ($variables['view']->result as $id => &$result) {
//            $node = $result->_entity;
//            $drupField = new DrupEntityField($node);
//
//            // Row attributes
//            $attributes = $variables['rows'][$id]['attributes'];
//            $attributes->addClass('list-item');
//
//            // Content
//            $result->title = $node->getTitle();
//            $result->url = $aliasManager->getAliasByPath('/node/' . $node->id());
//
//            // Add content
//            $variables['rows'][$id]['content'] = $result;
//            $variables['rows'][$id]['attributes'] = $attributes;
//        }
//    }
//
//    return $variables;
//}

/**
 * Toutes les vues
 */
function drup_theme_views_rows_controller($variables) {
    $viewId = $variables['view']->id();
    $displayId = $variables['view']->current_display;

    // Rows : valeurs par défaut liées au thème
    $variables['row_layout'] = 'third';
    $variables['row_image_style'] = 'item_primary';
    $variables['row_tag_title'] = 'h3';

    if ($viewId === 'news') {
        switch ($displayId) {
            case 'similar_content':
                $variables['row_layout'] = 'quarter';
                break;
        }
    }

    return $variables;
}

/**
 * Vue rows primary
 */
function drup_theme_views_rows_controller__primary($variables) {
    $languageId = \Drupal::languageManager()->getCurrentLanguage()->getId();

    $variables['rows_attributes']->addClass('list--primary');

    if (!empty($variables['view']->result)) {
        foreach ($variables['view']->result as $id => &$result) {
            $node = \Drupal::service('entity.repository')->getTranslationFromContext($result->_entity, $languageId);
            $drupField = $result->drupField = new DrupEntityField($node);
            
            $result->layout = $variables['row_layout'];
            $result->imageStyle = $variables['row_image_style'];
            $result->tagTitle = $variables['row_tag_title'];

            // Row attributes
            $attributes = $variables['rows'][$id]['attributes'];
            $attributes->addClass('list-item');
    
            // Media
            $mediaField = $drupField->get('image_thumbnail');
    
            // partial
            if (isset($result->partial)) {
                $attributes->addClass('l-'.$result->partial);
            }
            // Layout
            if (!empty($result->layout)) {
                $attributes->addClass('l-' . $result->layout);
            }

            // Content
            $result->title = $node->getTitle();
            $result->url = Url::fromUri('internal:/node/'.$node->id())->toString();

            // Add content
            $variables['rows'][$id]['content'] = $result;
            $variables['rows'][$id]['attributes'] = $attributes;
        }
    }

    return $variables;
}


/**
 * Implements hook_preprocess_views_infinite_scroll_pager().
 */
function drup_theme_preprocess_views_infinite_scroll_pager(&$vars) {
    $vars['btn_classes'] = 'btn';
    
    //if (isset($vars['parameters']['field_localisation_proximity'])) {
    //    $vars['btn_classes'] .= ' btn--link';
    //} else {
        $vars['btn_classes'] .= ' btn--primary l-arrow-bottom';
    //}
}
