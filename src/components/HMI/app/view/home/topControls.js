/**
 * @name MFT.ClimateView
 * 
 * @desc Climate module visual representation
 * 
 * @category	View
 * @filesource	app/view/climate/ClimateView.js
 * @version		2.0
 *
 * @author		Artem Petrosyan
 */
 
MFT.TopControls = Em.ContainerView.extend({
	
	elementId:			'app_top_menu_cont',
	
	childViews: [
		'controls',
		'toggleFAQButton'
	],
	
	controls: Em.ContainerView.extend({
		elementId:		'top_controls',
		
		
		childViews: [
			'clock',
//			'vSeparator',
			'toggleHelpButton',
		],
		
		clock: Em.View.extend({
			elementId:			'clock',
			
			classNameBindings: ['FLAGS.HELP_MODE:mcs'],
					
			afterRender: function() {
				MFT.SettingsController.getTime(new Date);
												
				setInterval(function(){
					MFT.SettingsController.getTime(new Date);
				},60000);
			},
			
			template: Em.Handlebars.compile('<div id="time_num">{{MFT.SettingsController.time}}</div>'),
			
			
			disableClock: function(){
				if(MFT.States.settings.clock.active){
					MFT.SettingsController.set('time','--:--');
				}else{
					MFT.SettingsController.getTime(new Date);
				}
			}.observes('MFT.States.settings.clock.active'),
			
			
			actionDown: function(event) {
				// Click handeler
				MFT.States.goToState('settings.clock');
				
				// return if state view loaded
				if ( MFT.States.currentState.viewLoaded ) {
					return;
				}
				
				// add observer on active state to hide left menu
				MFT.States.currentState.addObserver('active', function(){
					if (this.active) {
						MFT.SettingsClockView.listClockSettings.set('currentPage',1);
					}
				});				
			}
		}),
		
		vSeparator: Em.View.extend({
			elementId:	'top_controls_separator',
			
			classNameBindings: ['FLAGS.HELP_MODE:visible'],
			
			classNames: 'help_dev'
		}),
		
		toggleHelpButton: MFT.Button.extend({
			elementId:		'help',
			
			indClassBinding:	Em.Binding.oneWay('MFT.helpMode'),
			
			hidden:			!FLAGS.HELP_MODE,
					
			template: Em.Handlebars.compile(
				'<div class="inact" {{bindAttr class="view.indClass:act"}}></div>'+
				'<div id="sing" class="white" {{bindAttr class="view.indClass:yellow"}}></div>'+
				'<div id="help-p"></div>'
			),
			
			/** Toggle Help mode */
			actionDown: function(event) {
				if ( FLAGS.HELP_MODE ) {
					return;
				}
			
				MFT.toggleProperty('helpMode');
				
				/** Switch off video player if active */
				if(MFT.VideoPlayerController.model.isReady) MFT.VideoPlayerController.stop(); 
				
				/** Close FAQ state if active */
				if( MFT.States.faq.active ) {
					MFT.States.goToState(MFT.States.faq.from);
				}
				
				this._super();
			}
		})
	}),

	toggleFAQButton: MFT.Button.extend({
		elementId:			'faq_btn',
		
		// for helpmode
		classNames:			['faq_show'],
		
		activeBinding:		Em.Binding.oneWay('MFT.States.faq.active'),
			
		template: Ember.Handlebars.compile(
			'<div id="faq_btn_c"></div>'+
			'<div class="ind_inact" {{bindAttr class="view.active:ind_act"}}></div>'
		),
		
		actionDown: function() {
			if (MFT.States.faq.active) {
				MFT.States.goToState(MFT.States.faq.from);
			} else {
				MFT.States.goToState('faq');
			}
			
			this._super();
		}
	})
});