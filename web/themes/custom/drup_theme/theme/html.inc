<?php

Use Drupal\Core\Template\Attribute;
Use Drupal\Component\Utility\Html;
Use Drupal\drup\CookieNotice;

Use Drupal\drup\DrupCommon;

/**
/**
 * Implements hook_preprocess_HOOK() for html.html.twig.
 */
function drup_theme_preprocess_html(array &$variables) {
    $drupSettings = \Drupal::service('drup_settings.variables');
    $drupRouter = \Drupal::service('drup_router.router');

    // JS variables
    $variables['#attached']['drupalSettings']['pathToTheme'] = '/' . drupal_get_path('theme', 'drup_theme');

    // Body classes
    if (!($variables['attributes'] instanceof Attribute)) {
        $variables['attributes'] = new Attribute();
    }
    if ($variables['logged_in']) {
        $variables['attributes']->addClass('is-logged-in');
    }
    if ($variables['root_path'] === false) {
        $variables['attributes']->addClass('is-front');
    } else {
        $pageEntity = DrupCommon::getPageEntity();
        if ($pageEntity->type && $pageEntity->bundle) {
            $variables['attributes']->addClass([
                'entity-type--' . Html::cleanCssIdentifier($pageEntity->type),
                'entity-bundle--' . Html::cleanCssIdentifier($pageEntity->bundle)
            ]);
        }
    }
    if (isset($variables['node_type'])) {
        $variables['attributes']->addClass('node-type--' . Html::cleanCssIdentifier($variables['node_type']));
    }
    if ($routeName = $drupRouter->getName()) {
        $variables['#attached']['drupalSettings']['currentRoute'] = $routeName;
        $variables['attributes']->addClass('route--' . Html::cleanCssIdentifier($routeName));
    }
    
    // User role @see module drup_admin_toolbar
    
    $variables['google_tag'] = null;
    if (($googleTag = $drupSettings->getValue('site_tag_manager')) && (CookieNotice\Service::isAllowed('googletagmanager')) || !CookieNotice\Service::hasConsent()) {
        $variables['google_tag'] = $googleTag;
    }
    
    DrupCommon::addFavicons($variables, ['color_mask_icon' => '#5bbad5', 'color_msapplication' => '#da532c', 'color_theme' => '#ffffff'], 1);
}
