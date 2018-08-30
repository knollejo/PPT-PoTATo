import common

plots = common.PlotManager(
    # Observables
    common.SimpleObservable(
        'leptonPt[0]', nbins=20, xmin=0.0, xmax=200.0,
        short='lep1pt', xtitle='1st lepton p_{T} [GeV]',
        fields=common.Field('leptonPt', 'float', True),
    ),

    # Selection steps
    common.Selection(),

    # Categories
    common.Category(),

    # Event streams
    common.EventStreams.Data2017(name='test', title='data'),

    # Options
    short='test',
    luminosity='Name',
)
